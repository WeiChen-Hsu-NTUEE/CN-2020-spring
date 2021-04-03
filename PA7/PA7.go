package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strconv"
	"strings"
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
	// executing forever
	for {
		conn, _ := ln.Accept()

		reader := bufio.NewReader(conn)

		file_name := "" 
		count := 0 // counting whether to store the tokens[1] or not.

		// warning: each request will be divided into 5 parts (\r\n included)
		// we only need the tokens[1] of the first parts, which is the file name
		// other request message can be ignored
		// can'access to tokens outside this for loop, so we declare "file_name" previously 
		for {
			req, err := reader.ReadString('\n')  // read 1 line at a time
			check(err)
			if req == "\r\n" {  // means the last line of the http request
				break
			}
			tokens := strings.Split(req, " ")

			// remove "/" in the front of the "file_name"
			if count == 0 {
				file_name = strings.Replace(tokens[1], "/", "", -1)
			}
			count += 1
		}

		// try to access to the file
		file, err := os.Open(file_name)
		defer file.Close()

		// if the file exist
		if err == nil {
			file_size, _ := file.Stat()

			// convert the file_size from int64 to string
			str_file_size := strconv.FormatInt(file_size.Size(), 10)

			fmt.Println("File Size =", str_file_size)
		} else{
			fmt.Println("File Not Found")
		}
		conn.Close()
	}
}