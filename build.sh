# Pull pybind11 
git submodule init
git submodule update --remote

# Install EIGEN
THIRDPARTY_PATH=./thirdparty
EIGEN_REPO=https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
mkdir -p ${THIRDPARTY_PATH}
wget ${EIGEN_REPO} -O ${THIRDPARTY_PATH}/eigen-3.4.0.zip
pushd ${THIRDPARTY_PATH}
unzip eigen-3.4.0.zip -d eigen-3.4.0
cd eigen-3.4.0
make -j8
make install
popd

# Build poselib for different Python versions
python_versions=("3.7" "3.8" "3.9" "3.10")

for version in "${python_versions[@]}"
do
    conda create -y -n python${version} python=${version}
    source activate python${version}
    python setup.py bdist_wheel
    conda deactivate
done
