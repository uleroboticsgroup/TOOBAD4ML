Run as 

`docker run -v path_to_toobad4ml:/toobad4ml -it toobad4ml`

then

`mkdir /toobad4ml/build && cd /toobad4ml/build && conan install ..` 

To run we have to add the dependencies:

`export LD_LIBRARY_PATH=/root/.conan/data/llvm/6.0.0/Manu343726/testing/package/974d74a6fee14166dabe89430424dd5819713b82/lib/`

To dump AST:

`clang-check -ast-dump myfile.c`

we can use the dump from the AST to find line and column numbers of the sink 

(*sink: instruction where the buffer overflow is produced*)