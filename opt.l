%%
-a	ANLZ = 1;
-d	DEBG = 1;
-l	LY = 1;
-v	VERBOSE = 1;
-1	TO = 1;
-f=[0-9]+	sscanf(__REGISTER_PREFIX__ ogtext_r+3,"%u",&TOMEAS);
-f=.+	printf("Text Format Music: Malformed -f=firstmeasure\n");
-f=?	printf("Text Format Music: -f=firstmeasure option requires an argument\n");
a.tfm	{
		if (stdin NN) exit(1);
		yyin = fopen(__REGISTER_PREFIX__ ogtext_r,"r");
		if (yyin EN && printf("Unrecognized option or file not found: %s \n", __REGISTER_PREFIX__ ogtext_r)) exit(1);
	goto enddd;
	}
%%
