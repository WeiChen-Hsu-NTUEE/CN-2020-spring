package main
import "fmt"
import "bufio"
import "net"
import "strings"
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
		req, err := reader.ReadString('\n')  // read 1 line at a time
		check(err)
		if req == "\r\n" {  // means the last line of the http request
			break
		}
		tokens := strings.Split(req, " ")

		for i := range tokens {
			fmt.Println(i, tokens[i])
		}
	}
}
