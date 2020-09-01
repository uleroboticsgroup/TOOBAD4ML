# TOOBAD4ML

## DESCRIPTION

Ready to use container for the TOOBAD4ML tool. 

Run it as

`docker run -v $PATH_TO_FILE:$DESTINATION_PATH -it toobad4ml`

If you want to check the help section:

`docker run --rm -it toobad4ml -help`

To use the Padmanabhuni feature set run:

`docker run --rm -v $PATH_TO_FILE:$DESTINATION_PATH_OF_FILE -it toobad4ml -d Padmanabhuni $DESTINATION_PATH_OF_FILE`

To output the results to file:

`docker run --rm -v $PATH_TO_FILE:$DESTINATION_PATH_OF_FILE -v $OUTPUT_DESTINATION_FOLDER:$OUTPUT_DESTINATION_FOLDER -it toobad4ml -d Padmanabhuni -f CSV -o $OUTPUT_DESTINATION_FOLDER/output.csv $DESTINATION_PATH_OF_FILE`