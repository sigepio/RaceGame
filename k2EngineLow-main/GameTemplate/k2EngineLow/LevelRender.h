#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow {

	struct LevelObjectData2 {
		Vector3 position;	//���W
		Quaternion rotation;	//��]
		Vector3 scale;		//�g�嗦
		const wchar_t* name;	//���O
		int number = 0;

		//�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
		//���O�������ꍇ��true��Ԃ��܂��B
		bool EqualObjectName(const wchar_t* objName)//���ׂ閼�O
		{
			return wcscmp(objName, name) == 0;
		}
		//���O���O����v���邩���ׂ�
		bool ForwardMatchName(const wchar_t* n) {
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//���O�������B�s��v�B
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};

	class LevelRender:public Noncopyable
	{
	private:
	public:
		~LevelRender();

		//����������
		void Init(const char*filePath, std::function<bool(LevelObjectData2&objData)>hookFunc);

	private:
		//tkl�t�@�C���̍s���ύX����
		void MatrixRklToLevel();

	private:
		using BonePtr = std::unique_ptr<Bone>;
		std::vector<BonePtr>m_bonelist;
		std::unique_ptr<Matrix[]>m_matrixlist;
		TklFile m_tklFile;
	};
}

