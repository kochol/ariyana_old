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

		std::shared_ptr<T> Load(const std::string& filename,	void* extraParams)
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
			const uint32_t handle = GetNewHandle();

			if (!LoadResource(&pResource, handle, filename, extraParams))
				return nullptr;

			return AddResource(pResource);
		}

		void AddLoader(ResourceLoader* pLoader)
		{
			m_vLoaders.push_back(pLoader);
		}

		uint32_t GetNewHandle()
		{
			uint32_t handle;
			if (!m_sHandles.empty())
			{
				handle = m_sHandles.top();
				m_sHandles.pop();
			}
			else
			{
				handle = uint32_t(m_vResources.size());
			}
			return handle;
		}

		std::shared_ptr<T> AddResource(T* _resource)
		{			
			std::shared_ptr<T> sp(_resource);
			if (_resource->m_iHandle >= m_vResources.size())
				m_vResources.push_back(sp);
			else
				m_vResources[_resource->m_iHandle] = sp;

			return sp;
		}

	protected:

		virtual bool LoadResource(T** ppOut, uint32_t handle, const std::string& filename, 
			void* extraParams) = 0;

		std::vector<std::shared_ptr<T>>	m_vResources;		/**< Stores the resources */
		std::stack<uint32_t>			m_sHandles;			/**< Stores the unused handles number*/
		std::vector<ResourceLoader*>	m_vLoaders;			//!< Stores the resource loaders

	};
} // ari
