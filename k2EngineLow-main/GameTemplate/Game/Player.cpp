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



//セーブデータ
// XOR暗号化関数
void EncryptDecrypt(std::string& data, char key = 'K') {
    for (char& c : data) {
        c ^= key; // XORで暗号化/復号化
    }
}

// データを文字列に変換
std::string SerializeData(int RideCarNum, const std::vector<int>& PossessionCar, float Money, bool Transmission,
    const int LicenseClearStatus[5][5], bool ViewpointMode,
    float BGMVolume, float SEVolume, float EngineSoundVolume) {
    std::string data;
    data += std::to_string(RideCarNum) + "\n";
    data += std::to_string(Money) + "\n";
    data += std::to_string(Transmission) + "\n";
    data += std::to_string(ViewpointMode) + "\n";

    // Volume設定の追加
    data += std::to_string(BGMVolume) + "\n";
    data += std::to_string(SEVolume) + "\n";
    data += std::to_string(EngineSoundVolume) + "\n";

    data += "PossessionCar ";
    data += std::to_string(PossessionCar.size()) + " ";  // 車の数を保存
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

// セーブデータの書き込み
void SaveData(int RideCarNum, const std::vector<int>& PossessionCar, float Money, bool Transmission,
    const int LicenseClearStatus[5][5], bool ViewpointMode,
    float BGMVolume, float SEVolume, float EngineSoundVolume, const std::string& filename) {
    std::string data = SerializeData(RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume);

    // 暗号化
    EncryptDecrypt(data);

    // ファイルに書き込み
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        outfile << data;
        outfile.close();
    }
    else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

// データの読み込み
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

// デシリアライズ（読み込み処理）
void DeserializeData(const std::string& data, int& RideCarNum, std::vector<int>& PossessionCar, float& Money,
    bool& Transmission, int LicenseClearStatus[5][5], bool& ViewpointMode,
    float& BGMVolume, float& SEVolume, float& EngineSoundVolume) {
    std::istringstream iss(data);
    std::string temp;

    iss >> RideCarNum;
    iss >> Money;
    iss >> Transmission;
    iss >> ViewpointMode;

    // Volume設定の読み込み
    iss >> BGMVolume;
    iss >> SEVolume;
    iss >> EngineSoundVolume;

    iss >> temp; // "PossessionCar"
    int numCars;
    iss >> numCars;  // 車の数を取得
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

// セーブデータの読み込み
void LoadData(int& RideCarNum, std::vector<int>& PossessionCar, float& Money, bool& Transmission,
    int LicenseClearStatus[5][5], bool& ViewpointMode,
    float& BGMVolume, float& SEVolume, float& EngineSoundVolume, const std::string& filename) {
    std::string data = ReadFile(filename);

    // 暗号化されたデータを復号化
    EncryptDecrypt(data);

    // データを読み取ってオブジェクトに代入
    DeserializeData(data, RideCarNum, PossessionCar, Money, Transmission, LicenseClearStatus, ViewpointMode, BGMVolume, SEVolume, EngineSoundVolume);
}

bool Player::Start() {
    //ライセンスクリア状況の初期化
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