date=$(date -d '2 day ago' "+%Y%m%d")
echo $date
REGION_NAME=$1

if [ "$1" = "" ]
then
    echo "usage: ./multi_measure_2.sh [REGION_NAME]"
    exit 1
fi

start_time=`date +%s`

#mkdir ingress
#mkdir egress

mkdir ingress_${REGION_NAME}
mkdir egress_${REGION_NAME}

mkdir ingress_${REGION_NAME}_${date}
mkdir egress_${REGION_NAME}_${date}

./build.redhat.sh multi_measure

BASEDIR="/root/"

echo "copying..."
du -h ${BASEDIR}${date} 
time cp -r ${BASEDIR}${date} .
#time ./multi_measure $date list-${REGION_NAME}
export LD_LIBRARY_PATH=/root/boost_1_78_0/stage/lib; time ./multi_measure $date list-${REGION_NAME}

ls ./${date}/*ingress > list

while read line; do
    fn_src=`echo $line`
    fn_dst=`echo $line | cut -d "/" -f 3`
    cat header > tmp
    cat ${fn_src} >> tmp
    #echo "./ingress/${REGION_NAME}_${fn_dst}_${date}"
    cp tmp ./ingress_${REGION_NAME}_${date}/${REGION_NAME}_${fn_dst}_${date}
    mv tmp ./ingress_${REGION_NAME}/${REGION_NAME}_${fn_dst}_${date}
    #mv tmp ./ingress/${REGION_NAME}_${fn_dst}_${date}
done < list

ls ./${date}/*egress > list

while read line; do
    fn_src=`echo $line`
    fn_dst=`echo $line | cut -d "/" -f 3`
    cat header > tmp
    cat ${fn_src} >> tmp
    #echo "./egress/${REGION_NAME}_${fn_dst}_${date}"
    cp tmp ./egress_${REGION_NAME}_${date}/${REGION_NAME}_${fn_dst}_${date}
    mv tmp ./egress_${REGION_NAME}/${REGION_NAME}_${fn_dst}_${date}
    #mv tmp ./egress/${REGION_NAME}_${fn_dst}_${date}
done < list

rm -rf ${date}

end_time=`date +%s`
run_time=$((end_time - start_time))
run_time_minutes=`echo $(( ${run_time} / 60))`

echo "ELAPSED TIME:"${REGION_NAME}":"${date}":"$run_time":"$run_time_minutes

du -h ${BASEDIR}${date} 

#mv tmp ./egress_${REGION_NAME}/${REGION_NAME}_${fn_dst}_${date}

date=$(date -d '100 day ago' "+%Y%m%d")
rm -rf ./egress_${REGION_NAME}/${REGION_NAME}*${date}
rm -rf ./ingress_${REGION_NAME}/${REGION_NAME}*${date}

date=$(date -d '2 day ago' "+%Y%m%d")
echo $date
du -h ./ingress_${REGION_NAME}_${date}
du -h ./egress_${REGION_NAME}_${date}

#./build.sh cpu_reduction
#./build.redhat.sh multi_measure
./build.redhat.sh cpu_reduction

mkdir histo_ingress_${REGION_NAME}
mkdir histo_egress_${REGION_NAME}

start_time=`date +%s`
rm -rf tmp-counts
rm -rf tmp
export LD_LIBRARY_PATH=/root/boost_1_78_0/stage/lib; time ./cpu_reduction ./ingress_${REGION_NAME}_${date}
cat header-histo > tmp
cat tmp-counts >> tmp 
mv tmp ./histo_ingress_${REGION_NAME}/${date}

rm -rf tmp-counts
rm -rf tmp
export LD_LIBRARY_PATH=/root/boost_1_78_0/stage/lib; time ./cpu_reduction ./egress_${REGION_NAME}_${date}
cat header-histo > tmp
cat tmp-counts >> tmp 
mv tmp ./histo_egress_${REGION_NAME}/${date}


#scp -r egress_${REGION_NAME}_${date} 192.168.72.5:/mnt/sdd/nii-socs/
#scp -r ingress_${REGION_NAME}_${date} 192.168.72.5:/mnt/sdd/nii-socs/
