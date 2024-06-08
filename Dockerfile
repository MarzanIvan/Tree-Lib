FROM ubuntu AS build

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config

WORKDIR /opt/treeso

RUN mkdir -p /opt/treeso/external
ADD ./external /opt/treeso/external

RUN mkdir -p /opt/treeso/Testing
COPY /Testing/testing.cxx /Testing/docker-cmakelist/CMakeLists.txt /opt/treeso/Testing/

COPY CMakeLists.txt libTree_Lib.cpp libTree_Lib.hxx BalancedBinaryNode.hxx BalancedBinaryTree.hxx BinarySearchTree.hxx BinaryTree.hxx BinaryTreeNode.hxx ./

RUN cd /opt/treeso/Testing/ && cmake . && make && cd .. && cmake . && make
###CMD ["./opt/treeso/Testing/my_test"]

FROM ubuntu

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config


WORKDIR /opt/demo
# lib structure
RUN mkdir /opt/demo/treelib
RUN mkdir /opt/demo/treelib/bin
RUN mkdir /opt/demo/treelib/include
# copying lib files to lib structure package
COPY --from=build /opt/treeso/libTree_Lib.so /opt/demo/treelib/
COPY --from=build /opt/treeso/libTree_Lib.so /opt/demo/treelib/bin/
COPY --from=build /opt/treeso/*.hxx /opt/demo/treelib/
COPY --from=build /opt/treeso/*.hxx /opt/demo/treelib/include/

COPY /demo/docker-cmakelist/CMakeLists.txt /demo/main.cxx ./

RUN cd /opt/demo && cmake . && make

CMD ["./demo"]