#Examples

Here are some images that can be used for testing.

## Interactive mode
Two examples are provided for interactive mode
- [example 1](example_1_in.txt) -- 
- [example 2](example_2_in.txt)

Outputs are also captured.

These examples contain exit at the end, but if you wish to take over at the end, simly remove the last 2 lines.
And use cat to pipe the example into stdin and then take over the control.
```shell script
head -n -2 examples/example_2_in.txt examples/example_2_in_new.txt
cat examples/example_2_in_new.txt - | ./vernead2 
```

# CMD mode

To convert Image of duck to grayscale simply run
```shell script
./vernead2 --filter=grayscale examples/Images/duck.JPG examples/Images/duckGrayscale.jpg
```

To just convert image from PNG to JPG use
```shell script
./vernead2 examples/Images/progtest.png examples/Images/progtest.jpg
```

To print out PNG to STDOUT use
```shell script
./vernead2 examples/Images/progtest.png -
```

To use custom ASCII Lookup table use

```shell script
./vernead2 --ascii=examples/ascii examples/Images/progtest.png -
```