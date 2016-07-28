# srt Adjuster

Simple time adjuster for subtitles on .srt format.

## Dependencies

- G++ Compiler
- Linux ( or use the correspondent commands on Windows )

## How to use

First, you will need to compile the source code:

```bash
g++ -o name_of_the_executable srt_adjuster.cpp
```

Then, you need to run the following command.

```bash
cat subtitle_you_want_to_adjust.srt | name_of_the_executable time_to_adjust > subtitle_adjusted.srt
```

and time_to_adjust needs to be a integer or a double with a precision up to 3 decimal places.

Negative to advance and Positive to delay.

## Example

```bash
g++ -o srtAdjuster srt_adjuster.cpp
```

```bash
cat Les.Revenants.S02E01.FRENCH.HDTV.x264-LiBERTY.srt | srtAdjuster 5.333 > lesRevenants.srt
cat Les.Revenants.S02E01.FRENCH.HDTV.x264-LiBERTY.srt | srtAdjuster -5.333 > lesRevenants.srt
```
