#include "Audio.h"

ComPtr<IXAudio2> Audio::xAudio2;
IXAudio2MasteringVoice *Audio::masterVoice;

void Audio::Init()
{
    //xAudio�G���W���̃C���X�^���X�쐬
    HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    //�}�X�^�[�{�C�X�쐬
    result = xAudio2->CreateMasteringVoice(&masterVoice);
}

SoundData Audio::SoundLoadWave(const char *filename,bool loopFlag)
{
    //�t�@�C�����̓X�g���[���̃C���X�^���X
    std::ifstream file;
    //.wav�t�@�C�����o�C�i�����[�h�ŊJ��
    file.open(filename, std::ios_base::binary);
    //�I�[�v�����s�����o
    assert(file.is_open());

    //RIFT�w�b�_�[�ǂݍ���
    RiffHeader riff;
    file.read((char *)&riff, sizeof(riff));
    //�t�@�C����RIFT���`�F�b�N
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    //�^�C�v��WAVE���`�F�b�N
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }

    //�t�H�[�}�b�g�`�����N�̓ǂݍ���
    FormatChunk format = {};
    //�`�����N�w�b�_�[�̊m�F
    file.read((char *)&format, sizeof(ChunkHeader));
    //JUNK�`�����N���o��
    if (strncmp(format.chunk.id, "JUNK", 4) == 0)
    {
        //�ǂݎ����W�����N�`�����N�̏I���܂Ői�߂�
        file.seekg(format.chunk.size, std::ios_base::cur);
        //�ēǂݍ���
        file.read((char *)&format, sizeof(ChunkHeader));
    }
    if (strncmp(format.chunk.id, "fmt ", 4) != 0)
    {
        assert(0);
    }
    //�`�����N�{�̂̓ǂݍ���
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char *)&format.fmt, format.chunk.size);

    //Data�`�����N�̓ǂݍ���
    ChunkHeader data;
    file.read((char *)&data, sizeof(data));
    //JUNK�`�����N���o��
    if (strncmp(data.id, "JUNK", 4) == 0)
    {
        //�ǂݎ����W�����N�`�����N�̏I���܂Ői�߂�
        file.seekg(data.size, std::ios_base::cur);
        //�ēǂݍ���
        file.read((char *)&data, sizeof(data));
    }
    if (strncmp(data.id, "data", 4) != 0)
    {
        assert(0);
    }
    //data�`�����N�̃f�[�^�����ǂݍ���
    char *pBuffer = new char[data.size];
    file.read(pBuffer, data.size);
    //wav�����
    file.close();

    //�ԋp����f�[�^
    SoundData soundData = {};
    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE *>(pBuffer);
    soundData.bufferSize = data.size;
    soundData.sorceVoice = nullptr;

    HRESULT result;
    //�g�`�t�H�[�}�b�g�����ƂɃ\�[�X�̍쐬
    result = xAudio2->CreateSourceVoice(&soundData.sorceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    //�Đ�����g�`�f�[�^�̐ݒ�
    soundData.buf.pAudioData = soundData.pBuffer;
    soundData.buf.AudioBytes = soundData.bufferSize;
    soundData.buf.Flags = XAUDIO2_END_OF_STREAM;
    if (loopFlag)
    {
        soundData.buf.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    return soundData;
}

void Audio::SoundUnload(SoundData *data)
{
    //���������
    delete[] data->pBuffer;

    data->pBuffer = 0;
    data->bufferSize = 0;
    data->wfex = {};
}

void Audio::PlayLoadedSound(const SoundData &soundData,float volume)
{
    HRESULT result;

    result = soundData.sorceVoice->SetVolume(volume);
    //�g�`�f�[�^�Đ�
    result = soundData.sorceVoice->SubmitSourceBuffer(&soundData.buf);
    result = soundData.sorceVoice->Start();
}

void Audio::StopLoadedSound(SoundData &soundData)
{
    HRESULT result;

    //�g�`�f�[�^��~
    result = soundData.sorceVoice->Stop();
    result = soundData.sorceVoice->FlushSourceBuffers();
    result = soundData.sorceVoice->SubmitSourceBuffer(&soundData.buf);
}