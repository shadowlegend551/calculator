all:
	gcc -o main -O3 main.c readline.c tokenstack.c tokenqueue.c evaluator.c exceptions/exceptions.c exceptions/exceptionslib.c conversions.c token.c tokenizer.c isin.c functions.c constants.c parser.c -lm
