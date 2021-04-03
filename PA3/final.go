package main

import "fmt"
import "bufio"
import "net"
import "net/http"

func main() {
    ln, _ := net.Listen("tcp", ":12002")
    defer ln.Close()
    conn, _ := ln.Accept()
    defer conn.Close()

    reader := bufio.NewReader(conn)
    req, _ := http.ReadRequest(reader)

    fmt.Printf("Method: %s\n", req.Method)
    fmt.Printf("URI: %s\n", req.RequestURI)
}