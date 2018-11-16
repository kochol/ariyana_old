#pragma once
#include <string>
#include <vector>
#include <stack>

namespace ari
{	
	class ResourceLoader;

	template <class T>
	class ResourceManager
	{
	public:

		virtual ~ResourceManager() = default;

		std::shared_ptr<T> Load(const std::string filename,	void* extraParams)
		{
			// Searching for resource.
			for (const auto& res: m_vResources)
			{
				if (res)
				{
					if (!res->GetFileName().empty() && !filename.empty())
					{
						if (res->GetFileName() == filename)
						{							
							return res;
						}
					}
				}
			}

			// Resource not loaded yet.
			T* pResource = nullptr;
			uint32_t handle;
			bool add;
			if (m_sHandles.size() > 0)
			{
				handle = m_sHandles.top();
				m_sHandles.pop();
				add = false;
			}
			else
			{
				handle = (uint32_t)(m_vResources.size());
				add = true;
			}

			if (!LoadResource(&pResource, handle, filename, extraParams))
				return nullptr;

			// Add it to array
			std::shared_ptr<T> sp(pResource);
			if (add)
				m_vResources.push_back(sp);
			else
				m_vResources[handle] = sp;

			return sp;
		}

		void AddLoader(ResourceLoader* pLoader)
		{
			m_vLoaders.push_back(pLoader);
		}

	protected:

		virtual bool LoadResource(T** ppOut, uint32_t handle, const std::string& filename, 
			void* extraParams) = 0;

		std::vector<std::shared_ptr<T>>	m_vResources;		/**< Stores the resources */
		std::stack<uint32_t>			m_sHandles;			/**< Stores the unused handles number*/
		std::vector<ResourceLoader*>	m_vLoaders;			//!< Stores the resource loaders

	};
} // ari
