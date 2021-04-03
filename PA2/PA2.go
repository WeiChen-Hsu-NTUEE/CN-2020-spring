package main

import "fmt"
import "os"
import "bufio"
import "strconv"

func check (e error) {
	if e != nil {
		panic(e)
	}
}
func main(){
	fmt.Printf("input filename : ")
	input_text := ""
	fmt.Scanf("%s\n", &input_text)

	fmt.Printf("output filename : ")
	output_text := ""
	fmt.Scanf("%s\n", &output_text)

	f1, err1 := os.Open(input_text)
	check(err1)
	defer f1.Close()

    f2, err2 := os.Create(output_text)
    check(err2)
    defer f2.Close()

	scanner := bufio.NewScanner(f1)
	writer := bufio.NewWriter(f2)
	count := 0
	for scanner.Scan() {
		count++
		str_count := strconv.Itoa(count)
		len, _ := writer.WriteString(str_count)
		_ = len
		writer.Flush()
		len, _ = writer.WriteString(" ")
		_ = len
		writer.Flush()
		len, _ = writer.WriteString(scanner.Text())
		_ = len
		writer.Flush()
		len, _ = writer.WriteString("\n")
		_ = len
		writer.Flush()
	}

}