Building
========

Getting Source
--------------

.. code-block:: shell

    git clone https://github.com/kochol/ariyana.git
    cd ariyana
    git submodule update --init

Quick Start
-----------

These are step for users who use Windows with Visual Studio.

Enter ariyana directory:

.. code-block:: shell

    cd ariyana

Generate Visual Studio 2017 project files:

.. code-block:: shell

	deps\bx\tools\bin\windows\genie vs2017

Open ariyana solution in Visual Studio 2017:

.. code-block:: shell

	start .build\projects\vs2017\ariyana.sln

Generate Visual Studio 2017 project files with test projects:

.. code-block:: shell

	deps\bx\tools\bin\windows\genie --with-tests vs2017
