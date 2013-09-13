Alexander is a Neural Networks toolbox based on Benoit. It is licensed under the GPL v3, copyright Jack Hall (2011-2013). 

The best way to get Alexander is to clone this repository. 
You can also download the repository as a zip file, but then you will have to take care of updating it yourself. 
If you clone the repository, you can pull in changes and bugfixes directly from GitHub. 
It also makes contributing to Alexander easier, if you were interested in doing so. 

Alexander distributes with Benoit as a submodule. 
Benoit is another C++ that can represent message-passing networks. 
If you cloned Alexander to install, you will need to go to the Benoit directory and perform a git pull to get a copy. 

Alexander and Benoit are header-only libraries, so using them is as simple as putting the proper #include statements at the beginning of a file. 
Note that you will have to add Alexander/src and Alexander/Benoit/src to your include path so the compiler can find them.

The only other thing you'll need is a C++11 compatible compiler. 
Recent versions of clang, gcc, and MS Visual Studio should work. 
You might have to pass '-std=c++11' as a flag to your compiler so it knows to use the new standard.

