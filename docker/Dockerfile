FROM ubuntu:18.04

ENV CONAN_REVISIONS_ENABLED=1

RUN apt update && apt install -y cmake python3-pip

RUN pip3 install conan
RUN conan remote add roboticsgroup http://ciserver.unileon.es:9001/artifactory/api/conan/conan-dev

ENTRYPOINT [ "bash" ]