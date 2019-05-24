<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
# PROBLEM 3
记$f_{ij}$为有$i$个台阶，最后一次的台阶数为$j$的上楼方法数，则我们有下述递推式
$$f_{i1}=f_{i-1,2}+f_{i-1,3}$$
$$f_{i1}=f_{i-1,1}+f_{i-1,3}$$
$$f_{i1}=f_{i-1,1}+f_{i-1,2}$$
把$i=1,2,3$的情况都写出来，按照递推式即可求得
