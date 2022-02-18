cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd #
echo -e "\033[33m $(ls test_*.py|xargs)\033[0m" #
rm -rf *.pyc
ls
echo -e "\033[34m*******************OriginVM*******************\033[0m" #
total=0 #
success=0 #
error=0 #
for i in `ls test_*.py`;do  total=`echo $((total+=1))` ;t=`python2 -m compileall ${i};python2  ${i} |grep SUCCESS!!! |wc -l` ;if  [[ $t == 0 ]] ;then error=`echo $((error+=1))`;echo -e "\033[41m ${i}\033[0m";else success=`echo $((success+=1))`;fi ;done #
echo -e "\033[35m*******************SimpleVM*******************\033[0m" #
mtotal=0 #
msuccess=0 #
merror=0 #
for i in `ls test_*.pyc`;do  mtotal=`echo $((mtotal+=1))` ;t=`$1  $i |grep SUCCESS!!! |wc -l` ;if  [[ $t == 0 ]] ;then merror=`echo $((merror+=1))`;echo -e "\033[41m ${i}\033[0m";else msuccess=`echo $((msuccess+=1))`;fi ;done #
echo -e "\033[33m**********************************************\033[0m" #
echo -e "\033[33m**********************************************\033[0m" #
echo -e "\033[34m原生虚拟机结果\033[0m" #
echo -e "\033[34mtotal test case : ${total}\033[0m"
echo -e "\033[34msuccess test case : ${success}\033[0m"
echo -e "\033[34merror test case : ${error}\033[0m"
echo -e "\033[35mSimpleVM虚拟机结果\033[0m" #
echo -e "\033[35mtotal test case : ${mtotal}\033[0m"
echo -e "\033[35msuccess test case : ${msuccess}\033[0m"
echo -e "\033[35merror test case : ${merror}\033[0m"