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
	conn, _ := ln.Accept()
	defer ln.Close()
	defer conn.Close()

	reader := bufio.NewReader(conn)

	filesize, err := reader.ReadString('\n')
	filesize = strings.TrimSpace(filesize)
	filesizenum, err := strconv.Atoi(filesize)
	Outputfile, erro := os.Create("Whatever.txt")
	check(erro)

	buffer1 := ""
	buffer2 := make([]byte, 0)

	i := 1

	for {
		readlines, err := reader.ReadString('\n')
		buffer1 = buffer1 + readlines

		writer := bufio.NewWriter(Outputfile)
		readlines = strconv.Itoa(i) + " " + readlines
		buffer2 = []byte(readlines)
		n, err := writer.Write(buffer2)
		_ = n
		check(err)
		writer.Flush()

		if len(buffer1) >= filesizenum {
			break
		}

		i++

	}

	Outinfo, _ := Outputfile.Stat()
	Outfilesize := strconv.FormatInt(Outinfo.Size(), 10)
	fmt.Println("Upload file size:", filesize)
	fmt.Println("Output file size:", Outfilesize)

	write := bufio.NewWriter(conn)
	newline := fmt.Sprintf("%s bytes received, %s bytes generate\n", filesize, Outfilesize)
	ww, err := write.WriteString(newline)
	_ = ww
	check(err)
	write.Flush()

}
