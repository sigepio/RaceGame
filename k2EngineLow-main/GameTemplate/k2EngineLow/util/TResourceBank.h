#pragma once

#include <memory>

namespace nsK2EngineLow {
	template<class TResource>
	class TResourceBank : public Noncopyable {
	public:
		TResource* Get(const char* filePath)
		{
			auto it = m_resourceMap.find(filePath);
			if (it != m_resourceMap.end()) {
				//バンクに登録されている。
				return it->second.get();
			}
			return nullptr;
		}
		void Regist(const char* filePath, TResource* resource)
		{
			auto it = m_resourceMap.find(filePath);
			if (it == m_resourceMap.end()) {
				//未登録。
				m_resourceMap.insert(
					std::pair< std::string, TResourcePtr>(filePath, resource)
				);
			}
		}
		void Release()
		{
			// 全リソースを解放
			m_resourceMap.clear();
		}
		void Release(const char* filePath) {
			// 指定されたファイルパスのリソースを削除
			auto it = m_resourceMap.find(filePath);
			m_resourceMap.erase(it);
		}
	private:
		using TResourcePtr = std::unique_ptr<TResource>;
		std::map<std::string, TResourcePtr> m_resourceMap;
	};
}