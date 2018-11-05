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

		DelegateNoParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

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



	template <class Treturn, class Targ1>
	class DelegateOneParam
	{
		template <class Treturn, class Targ1>
		class BaseFuncOneParam
		{
		public:

			virtual Treturn Call(Targ1 arg1) = 0;
		};

		template <class Tclass, class Treturn, class Targ1>
		class MemFuncOneParam : public BaseFuncOneParam<Treturn, Targ1>
		{
		public:

			MemFuncOneParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1) override
			{
				return (*m_pObj.*m_pFun)(arg1);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1);
		};

	public:

		DelegateOneParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateOneParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1))
		{
			m_pMemFun = new MemFuncOneParam<Tclass, Treturn, Targ1>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1)
		{
			if (m_pFun)
				return m_pFun(arg1);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1);
		}

	protected:
		Treturn(*m_pFun)(Targ1);
		BaseFuncOneParam<Treturn, Targ1>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2>
	class DelegateTwoParam
	{
		template <class Treturn, class Targ1, class Targ2>
		class BaseFuncTwoParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2>
		class MemFuncTwoParam : public BaseFuncTwoParam<Treturn, Targ1, Targ2>
		{
		public:

			MemFuncTwoParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2);
		};

	public:

		DelegateTwoParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateTwoParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2))
		{
			m_pMemFun = new MemFuncTwoParam<Tclass, Treturn, Targ1, Targ2>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2);
		BaseFuncTwoParam<Treturn, Targ1, Targ2>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3>
	class DelegateThreeParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3>
		class BaseFuncThreeParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3>
		class MemFuncThreeParam : public BaseFuncThreeParam<Treturn, Targ1, Targ2, Targ3>
		{
		public:

			MemFuncThreeParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3);
		};

	public:

		DelegateThreeParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateThreeParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3))
		{
			m_pMemFun = new MemFuncThreeParam<Tclass, Treturn, Targ1, Targ2, Targ3>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3);
		BaseFuncThreeParam<Treturn, Targ1, Targ2, Targ3>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4>
	class DelegateFourParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4>
		class BaseFuncFourParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4>
		class MemFuncFourParam : public BaseFuncFourParam<Treturn, Targ1, Targ2, Targ3, Targ4>
		{
		public:

			MemFuncFourParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4);
		};

	public:

		DelegateFourParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateFourParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4))
		{
			m_pMemFun = new MemFuncFourParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4);
		BaseFuncFourParam<Treturn, Targ1, Targ2, Targ3, Targ4>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5>
	class DelegateFiveParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5>
		class BaseFuncFiveParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5>
		class MemFuncFiveParam : public BaseFuncFiveParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5>
		{
		public:

			MemFuncFiveParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5);
		};

	public:

		DelegateFiveParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateFiveParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5))
		{
			m_pMemFun = new MemFuncFiveParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5);
		BaseFuncFiveParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6>
	class DelegateSixParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6>
		class BaseFuncSixParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6>
		class MemFuncSixParam : public BaseFuncSixParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6>
		{
		public:

			MemFuncSixParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5, arg6);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6);
		};

	public:

		DelegateSixParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateSixParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6))
		{
			m_pMemFun = new MemFuncSixParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5, arg6);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5, arg6);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6);
		BaseFuncSixParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7>
	class DelegateSevenParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7>
		class BaseFuncSevenParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7>
		class MemFuncSevenParam : public BaseFuncSevenParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>
		{
		public:

			MemFuncSevenParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7);
		};

	public:

		DelegateSevenParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateSevenParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7))
		{
			m_pMemFun = new MemFuncSevenParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7);
		BaseFuncSevenParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8>
	class DelegateEightParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8>
		class BaseFuncEightParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8>
		class MemFuncEightParam : public BaseFuncEightParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8>
		{
		public:

			MemFuncEightParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8);
		};

	public:

		DelegateEightParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateEightParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8))
		{
			m_pMemFun = new MemFuncEightParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8);
		BaseFuncEightParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9>
	class DelegateNineParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9>
		class BaseFuncNineParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9>
		class MemFuncNineParam : public BaseFuncNineParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9>
		{
		public:

			MemFuncNineParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9);
		};

	public:

		DelegateNineParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateNineParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9))
		{
			m_pMemFun = new MemFuncNineParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9);
		BaseFuncNineParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9>	*	m_pMemFun;
	};



	template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9, class Targ10>
	class DelegateTenParam
	{
		template <class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9, class Targ10>
		class BaseFuncTenParam
		{
		public:

			virtual Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9, Targ10 arg10) = 0;
		};

		template <class Tclass, class Treturn, class Targ1, class Targ2, class Targ3, class Targ4, class Targ5, class Targ6, class Targ7, class Targ8, class Targ9, class Targ10>
		class MemFuncTenParam : public BaseFuncTenParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10>
		{
		public:

			MemFuncTenParam(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10)) : m_pObj(_obj), m_pFun(_fun) {}

			Treturn Call(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9, Targ10 arg10) override
			{
				return (*m_pObj.*m_pFun)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			}

		protected:

			Tclass	*	m_pObj;
			Treturn(Tclass::*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10);
		};

	public:

		DelegateTenParam() : m_pFun(nullptr), m_pMemFun(nullptr) { }

		~DelegateTenParam()
		{
			delete m_pMemFun;
		}

		void Bound(Treturn(*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10)) { m_pFun = _fun; }

		template <class Tclass>
		void Bound(Tclass* _obj, Treturn(Tclass::*_fun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10))
		{
			m_pMemFun = new MemFuncTenParam<Tclass, Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10>(_obj, _fun);
		}

		bool IsBound() { return m_pFun || m_pMemFun; }

		Treturn Execute(Targ1 arg1, Targ2 arg2, Targ3 arg3, Targ4 arg4, Targ5 arg5, Targ6 arg6, Targ7 arg7, Targ8 arg8, Targ9 arg9, Targ10 arg10)
		{
			if (m_pFun)
				return m_pFun(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			if (m_pMemFun)
				return m_pMemFun->Call(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}

	protected:
		Treturn(*m_pFun)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10);
		BaseFuncTenParam<Treturn, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7, Targ8, Targ9, Targ10>	*	m_pMemFun;
	};



}