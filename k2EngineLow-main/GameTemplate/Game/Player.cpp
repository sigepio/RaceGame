#include "stdafx.h"
#include "Player.h"
#include "vector"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring> // for memset

Player::Player() {

}

Player::~Player() {

}



//�Z�[�u�f�[�^
// XOR�Í����֐�
void EncryptDecrypt(std::string& data, char key = 'K') {
    for (char& c : data) {
        c ^= key; // XOR�ňÍ���/������
    }
}

// �f�[�^�𕶎���ɕϊ�
std::string SerializeData(int RideCarNum, const std::vector<int>& PossessionCar, float Money, bool Transmission,
    const int LicenseClearStatus[5][5], bool ViewpointMode,
    float BGMVolume, float SEVolume, float EngineSoundVolume) {
    std::string data;
    data += std::to_string(RideCarNum) + "\n";
    data += std::to_string(Money) + "\n";
    data += std::to_string(Transmission) + "\n";
    data += std::to_string(ViewpointMode) + "\n";

    // Volume�ݒ�̒ǉ�
    data += std::to_string(BGMVolume) + "\n";
    data += std::to_string(SEVolume) + "\n";
    data += std::to_string(EngineSoundVolume) + "\n";

    data += "PossessionCar ";
    data += std::to_string(PossessionCar.size()) + " ";  // �Ԃ̐���ۑ�
    for (int car : PossessionCar) {
        data += std::to_string(car) + " ";
    }
    data += "\n";

    data += "LicenseClearStatus ";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            data += std::to_string(LicenseClearStatus[i][j]) + " ";
        }
    }
    data += "\n";

    return data;
}

// �Z�[�u�f�[�^�̏�������
void SaveData(int RideCarNum, const std::vector<int>& PossessionCar, float Money, bool Transmission,
    const int LicenseClearStatus[5][5], bool ViewpointMode,
    float BGMVolume, float SEVolume, float EngineSoundVolume, const std::string& filename) {
    std::string data = SerializeData(RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume);

    // �Í���
    EncryptDecrypt(data);

    // �t�@�C���ɏ�������
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        outfile << data;
        outfile.close();
    }
    else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

// �f�[�^�̓ǂݍ���
std::string ReadFile(const std::string& filename) {
    std::ifstream infile(filename, std::ios::binary);
    std::string data;

    if (infile.is_open()) {
        infile.seekg(0, std::ios::end);
        data.resize(infile.tellg());
        infile.seekg(0, std::ios::beg);
        infile.read(&data[0], data.size());
        infile.close();
    }
    else {
        std::cerr << "Failed to open file for reading." << std::endl;
    }

    return data;
}

// �f�V���A���C�Y�i�ǂݍ��ݏ����j
void DeserializeData(const std::string& data, int& RideCarNum, std::vector<int>& PossessionCar, float& Money,
    bool& Transmission, int LicenseClearStatus[5][5], bool& ViewpointMode,
    float& BGMVolume, float& SEVolume, float& EngineSoundVolume) {
    std::istringstream iss(data);
    std::string temp;

    iss >> RideCarNum;
    iss >> Money;
    iss >> Transmission;
    iss >> ViewpointMode;

    // Volume�ݒ�̓ǂݍ���
    iss >> BGMVolume;
    iss >> SEVolume;
    iss >> EngineSoundVolume;

    iss >> temp; // "PossessionCar"
    int numCars;
    iss >> numCars;  // �Ԃ̐����擾
    PossessionCar.clear();
    for (int i = 0; i < numCars; ++i) {
        int car;
        iss >> car;
        PossessionCar.push_back(car);
    }

    iss >> temp; // "LicenseClearStatus"
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            iss >> LicenseClearStatus[i][j];
        }
    }
}

// �Z�[�u�f�[�^�̓ǂݍ���
void LoadData(int& RideCarNum, std::vector<int>& PossessionCar, float& Money, bool& Transmission,
    int LicenseClearStatus[5][5], bool& ViewpointMode,
    float& BGMVolume, float& SEVolume, float& EngineSoundVolume, const std::string& filename) {
    std::string data = ReadFile(filename);

    // �Í������ꂽ�f�[�^�𕜍���
    EncryptDecrypt(data);

    // �f�[�^��ǂݎ���ăI�u�W�F�N�g�ɑ��
    DeserializeData(data, RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume);
}

bool Player::Start() {
    //���C�Z���X�N���A�󋵂̏�����
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            LicenseClearStatus[i][j] = 0;
        }
    }
    LoadData(RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume, "savedata.txt");
    return true;
}

void Player::Save() {
    SaveData(RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume, "savedata.txt");
}

void Player::Update() {

}