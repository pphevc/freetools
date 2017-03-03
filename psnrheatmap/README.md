# HeatMap :
HeatMap is a tool which takes input parameters and performs color overlay based one peak signal  
to noise ratio(PSNR). 

# Why HeatMap Tool :
Overlay helps in seeing one or more bad frame in a sequence, a region within a frame, block or a  
group of blocks with a region, which may or may not be easily detectable to the naked eye.

# Support :
Chroma format : 420 only  
Bitdepth            : 8  
PlanarYUV  
NOTE                : 422, 10bit support could be added later

# Color Scale :
![color_scale](https://cloud.githubusercontent.com/assets/25979247/23543191/1be036d2-0017-11e7-8b95-655b97a24106.png)

# Sample Usage :
## Linux :
HeatMap -r reference_input.yuv -o original_input.yuv -w width -h height -f number_of_frames -b block_size  

##Windows :
HeatMap.exe  -r reference_input.yuv -o original_input.yuv -w width -h height -f number_of_frames -b block_size  

# Sample OutPut:
We can get output for different block sizes but for reference we are attaching screen shot for block size 4, 8 and 32 

original  
![original](https://cloud.githubusercontent.com/assets/25979247/23543223/492bf900-0017-11e7-8f03-63a836c9c088.PNG)  
HeatMapped(b=4)  
![heatmapped_b_4](https://cloud.githubusercontent.com/assets/25979247/23543249/65f30358-0017-11e7-8476-c8cb1cb78a1c.PNG)  
HeatMapped(b=8)  
![heatmapped_b_8](https://cloud.githubusercontent.com/assets/25979247/23543271/74c08838-0017-11e7-9983-341ccf03ac6b.PNG)  
HeatMapped(b=32)  
![heatmapped_b_32](https://cloud.githubusercontent.com/assets/25979247/23543288/87a12c00-0017-11e7-9bc8-172560923b89.PNG)
