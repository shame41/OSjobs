cmd_/home/shame41/2022work/hust_se_oslab/OSjobs/lab4/modules.order := {   echo /home/shame41/2022work/hust_se_oslab/OSjobs/lab4/hello.ko; :; } | awk '!x[$$0]++' - > /home/shame41/2022work/hust_se_oslab/OSjobs/lab4/modules.order
