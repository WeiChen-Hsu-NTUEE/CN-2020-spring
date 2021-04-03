package main

import (
	"fmt"
	"net/http"
	"net/url"
	"os"
	"path/filepath"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	fmt.Println("Launching server...")
	hd := http.HandlerFunc(Handle)
	http.Handle("/", hd)
	http.ListenAndServe(":12002", nil)

}

func ListDir() (files []string) {
	root := "."
	err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		files = append(files, path)
		return nil
	})
	if err != nil {
		panic(err)
	}
	return files
}

func Handle(w http.ResponseWriter, r *http.Request) {
	files := ListDir()
	filepath := strings.TrimPrefix(r.URL.Path, "/")

	exists := false
	for _, f := range files {
		if f == filepath {
			//fmt.Fprintln(w, "File Exist")
			fs := http.FileServer(http.Dir("."))
			r2 := new(http.Request)
			*r2 = *r
			r2.URL = new(url.URL)
			*r2.URL = *r.URL
			r2.URL.Path = filepath
			fs.ServeHTTP(w, r2)
			exists = true
			break
		}
	}
	if !exists {
		fmt.Fprintln(w, "File Not found")
	}

}
