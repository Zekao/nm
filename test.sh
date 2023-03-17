#/bin/sh

make > /dev/null || exit 1

./ft_nm $@ > ft_nm_output &
nm $@ > nm_output &
wait

diff -U 1 ft_nm_output nm_output

rm ft_nm_output nm_output