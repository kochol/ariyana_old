#pragma once

namespace ari
{
	template <class Treturn>
	class DelegateNoParam
	{
		template <class Treturn>
		class BaseFuncNoParam
		{
		public:

			virtual Treturn Call() = 0;
		};

		template <class Tclass, class Treturn>
		class MemFuncNoParam : public BaseFuncNoParam<Treturn>
		{
		public:

			MemFuncNoParam(Tclass* _obj, Treturn(Tclass::*_fun)()) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call() override
			{
				return (*m_pObj.*m_pFun)();
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)();
		};

	public:

		DelegateNoParam(): m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateNoParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)()) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)())
		{
			m_pMemFun = new MemFuncNoParam<Tclass, Treturn>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute()
		{
			if (m_pFun)
				return m_pFun();
			if (m_pMemFun)
				return m_pMemFun->Call();		
		}

	protected:
		Treturn(*m_pFun)();
		BaseFuncNoParam<Treturn>	*	m_pMemFun;
	};
}