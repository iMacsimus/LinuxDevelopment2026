set args 1 12

break print_range
run

watch n
commands
    silent
    if n%5 == 0
        printf "@@@ start=%02ld stop=%02ld step=%02ld elem=%02ld\n", start, stop, step, n
    end
    continue
end
continue
quit