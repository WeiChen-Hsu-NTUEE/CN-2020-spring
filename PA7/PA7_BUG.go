package main
//import "io"
import (
	"bufio"
	"fmt"
	"net"
	//	"os"
	"strings"
	//	"strconv"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	fmt.Println("Launching server...")
	ln, _ := net.Listen("tcp", ":12002")
	defer ln.Close()
	conn, _ := ln.Accept()
	defer conn.Close()

	reader := bufio.NewReader(conn)
	for {
		for {
			req, err := reader.ReadString('\n')  // read 1 line at a time
			check(err)
			if req == "\r\n" {  // means the last line of the http request
				break
			}
			tokens := strings.Split(req, " ")
			fmt.Println(tokens)
		}
		fmt.Println("11111")

		/*
			// remove the "/" in the front of the tokens[1]
			 file_name := strings.Replace(tokens[1], "/", "", -1)

			// open the file
			file, err := os.Open(file_name)

			fmt.Println("err = ", err)

			defer file.Close()

			// the file exist
			if (err == nil){
				// get the file size
				file_size, _ := file.Stat()

				// convert the file_size from int64 to string
				str_file_size := strconv.FormatInt(file_size.Size(), 10)
				// print the file size
				fmt.Println("File Size =  ", str_file_size)
			} else {
				fmt.Println("File not found")
			  }
		*/
	}
}

