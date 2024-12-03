# Requirements
sudo apt-get -y install python3-dev python3-numpy python3-nose libboost-python-dev libboost-numpy-dev
git clone git@github.com:ARC-OPT/wbc_py.git
mkdir wbc_py/build
cd wbc_py/build
cmake .. && make -j8
sudo make install


