all: callcenter customer callcenter_rm

customer:
	gcc -o customer -pthread customer.c 

callcenter_rm:
	gcc -o callcenter_rm -pthread callcenter_rm.c 

callcenter:
	gcc -o callcenter -pthread callcenter.c 

clean:
	rm callcenter customer callcenter_rm

