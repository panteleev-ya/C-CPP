$sum = 0
$prev_results = {"1" => 1}

# This function can be easily modified for more cases of steps by checking array of steps instead of multiple if's
def make_step(x)  # step options: 1, 2
    prev_known_result = $prev_results[x.to_s]  # if we already calculated this result previously
    if prev_known_result != nil
        $sum += prev_known_result
    else  # we do the calculation
        if x >= 1
            make_step(x - 1)
        end
        if x >= 2
            make_step(x - 2)
        end
        if x == 0
            $sum += 1
        else
            $prev_results[x.to_s] = $sum  # now we calculated the result
        end
    end
end

# @param {Integer} n
# @return {Integer}
def climb_stairs(n)
    make_step(n)
    sum = $sum
    $sum = 0
    return sum
end