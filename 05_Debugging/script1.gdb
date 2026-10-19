set args 1 12

break print_range
run

watch n
commands
    silent
    if n%5 == 0
        printf "@@@ n=%02ld start=%02ld stop=%02ld step=%02ld\n", n, start, stop, step
    end
    continue
end
continue
quit