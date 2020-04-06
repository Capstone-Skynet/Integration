./ml_server &
sleep 2s
python3 pythonClient/pythonClient.py &
sleep 2s
ssh root@192.168.1.10 "cd /home/root/ml/runfiles/ && mlprog"
