package main

import (
	"bufio"
	"fmt"
	"io"
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
func fillString(retunString string, toLength int) string {
	for {
		lengtString := len(retunString)
		if lengtString < toLength {
			retunString = retunString + ":"
			continue
		}
		break
	}
	return retunString
}
func main() {
	//conn, errc := net.Dial("tcp", "140.112.42.161:11999")
	conn, errc := net.Dial("tcp", "127.0.0.1:12002")
	check(errc)
	defer conn.Close()

	fmt.Printf("Input filename:")
	reader := bufio.NewReader(os.Stdin)
	filename, _ := reader.ReadString('\n')

	file, err := os.Open(strings.TrimSpace(filename))
	check(err)
	defer file.Close()
	stat, err := file.Stat()
	fmt.Println("Send the size of the file first:", stat.Size())

	//min fileSize size:10 bytes, min filenName size:64 bytes
	//fileSize := fillString(strconv.FormatInt(stat.Size(), 10), 10)
	//fileName := fillString(filename, 64)
	fileSize := strconv.FormatInt(stat.Size(), 10)
	//fileName := filename

	//send filename
	//_,err = conn.Write([]byte(fileName))
	check(err)
	//send filesize
	_, err = conn.Write([]byte(fileSize + "\n"))
	check(err)
	//create a buffer for i/o
	buffer := make([]byte, 1024)

	//start sending file
	for {

		_, err := file.Read(buffer)

		if err == io.EOF {
			break
		}
		_, err = conn.Write(buffer)
		check(err)
	}

	read := bufio.NewReader(conn)
	message, errr := read.ReadString('\n')
	check(errr)
	fmt.Printf("Server replies: %s ", message)
	//fmt.Println("Server says:", stat.Size() ,"bytes received")
}
