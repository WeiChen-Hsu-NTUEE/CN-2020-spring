package main

import (
	"bufio"
	"fmt"
	"net"
	"net/http"
	"os"
	"path/filepath"
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
	for {
		conn, _ := ln.Accept()
		//defer conn.Close()
		HttpInterprete(conn)
		conn.Close()
	}

}

func ListDir() (files []string, s []int64) {
	//var files []string
	//var s []int64

	root := "."
	err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		files = append(files, path)
		s = append(s, info.Size())
		return nil
	})
	if err != nil {
		panic(err)
	}
	//fmt.Println(files)
	//fmt.Println(s)
	return files, s
}

func HttpInterprete(conn net.Conn) {

	reader := bufio.NewReader(conn)
	req, err := http.ReadRequest(reader)
	check(err)
	//fmt.Println(req.URL.String()[1:])

	files, s := ListDir()
	index := 0
	for i, f := range files {
		//fmt.Println(i, f)
		if f == req.URL.String()[1:] {
			fmt.Println("Filesize =", s[i])
			index = i
			break
		}
		index = index + 1
	}
	if index == len(s) {
		fmt.Println("File Not found")
	}

}
