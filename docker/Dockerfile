FROM ubuntu:18.04

ENV CONAN_REVISIONS_ENABLED=1
ENV LD_LIBRARY_PATH=/root/.conan/data/llvm/6.0.0/Manu343726/testing/package/974d74a6fee14166dabe89430424dd5819713b82/lib/

RUN apt update && apt install -y cmake python3-pip clang clang-tools

RUN pip3 install conan
RUN conan remote add roboticsgroup http://ciserver.unileon.es:9001/artifactory/api/conan/conan-dev

ENTRYPOINT [ "bash" ]