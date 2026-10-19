set args -100 100 3
set $gdb_counter = 0

break print_range
run

watch n
commands
    silent
    set $gdb_counter = $gdb_counter + 1
    if 28 <= $gdb_counter && $gdb_counter <= 35
        printf "@@@ start=%02ld stop=%02ld step=%+02ld elem=%+03ld\n", start, stop, step, n
    end
    continue
end
continue
quit