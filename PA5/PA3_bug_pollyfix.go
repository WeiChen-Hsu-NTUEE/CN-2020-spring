package main
import (
	"fmt"
	"bufio"
	"net"
	"os"
	"strconv"
)
func check(e error) {
	if e != nil {
		panic(e)
	}
}
func main() {
// make the client connect to the server

	conn_client, errc := net.Dial("tcp", "127.0.0.1:12002")
	check(errc)
	defer conn_client.Close()
// prompt user for the inputfile name

	fmt.Printf("Input filename : ")
	input_filename := ""
	fmt.Scanf("%s\n", &input_filename)

// open the inputfile

	inputfile, errf := os.Open(input_filename) 
	check(errf)
	defer inputfile.Close()

// get the file size

	file_size, _ := inputfile.Stat() 

// convert the file_size from int64 to string

	str_file_size := strconv.FormatInt(file_size.Size(), 10)

	str_file_size = str_file_size + "\n"
// send the file_size to the server

	size_writer_of_client := bufio.NewWriter(conn_client)
	_, _ = size_writer_of_client.WriteString(str_file_size)
	size_writer_of_client.Flush()
// show the sent size

	fmt.Printf("Send the file size first : %s\n", str_file_size)
	
// initial couple of scanner and writer

	scanner_of_inputfile := bufio.NewScanner(inputfile)
	message_writer_of_client := bufio.NewWriter(conn_client)

// start scanning the inputfile     

	for scanner_of_inputfile.Scan() {


		// fmt.Printf("pass1\n")


		_, err1 := message_writer_of_client.WriteString(scanner_of_inputfile.Text()+"\n") // store the scanning result (message) into the writer
		check(err1)


		// fmt.Printf("pass2\n")


		message_writer_of_client.Flush()


		// fmt.Printf("pass3\n")


		// fmt.Printf("%s\n", scanner_of_inputfile.Text())



	}


	// fmt.Printf("pass4\n")

// declare the scanner of the srever response

	scanner_of_server_response := bufio.NewScanner(conn_client)

	// fmt.Printf("pass5\n")

// start scanning the response

	for scanner_of_server_response.Scan() {

		
		// fmt.Printf("pass6\n")
		

		fmt.Printf("server replies : %s\n", scanner_of_server_response.Text())


		// fmt.Printf("pass7\n")
	}
}
