1    2    int                                      1    1    1   
2    1    gcd_cal                                  1    5    1   
3    5    (                                        1    12   1   
4    2    int                                      1    13   2   
5    1    n1                                       1    17   1   
6    6    ,                                        1    19   1   
7    2    int                                      1    20   3   
8    1    n2                                       1    24   1   
9    5    )                                        1    26   1   
10   6    {                                        1    27   1   
11   2    int                                      2    1    4   
12   1    c                                        2    5    1   
13   5    =                                        2    6    1   
14   1    n1                                       2    7    2   
15   5    %                                        2    9    1   
16   1    n2                                       2    10   2   
17   6    ;                                        2    12   1   
18   2    if                                       3    1    1   
19   5    (                                        3    3    2   
20   1    c                                        3    4    2   
21   5    )                                        3    5    2   
22   6    {                                        3    6    2   
23   1    n2                                       4    1    3   
24   5    =                                        4    3    2   
25   1    gcd_cal                                  4    4    2   
26   5    (                                        4    11   3   
27   1    n2                                       4    12   4   
28   6    ,                                        4    14   2   
29   1    c                                        4    15   3   
30   5    )                                        4    16   3   
31   6    ;                                        4    17   2   
32   6    }                                        5    1    1   
33   2    return                                   6    1    1   
34   1    n2                                       6    8    5   
35   6    ;                                        6    10   3   
36   6    }                                        7    1    2   
37   2    int                                      8    1    5   
38   1    main                                     8    5    1   
39   5    (                                        8    9    4   
40   5    )                                        8    10   4   
41   6    {                                        8    11   3   
42   2    int                                      9    1    6   
43   1    a                                        9    5    1   
44   6    ,                                        9    6    3   
45   1    b                                        9    7    1   
46   6    ;                                        9    8    4   
47   1    scanf                                    10   1    1   
48   5    (                                        10   6    5   
49   1    a                                        10   7    2   
50   5    %                                        10   8    2   
51   1    d                                        10   9    1   
52   5    %                                        10   10   3   
53   1    d                                        10   11   2   
54   1    a                                        10   12   3   
55   6    ,                                        10   13   4   
56   5    &                                        10   14   1   
57   1    a                                        10   15   4   
58   6    ,                                        10   16   5   
59   5    &                                        10   17   2   
60   1    b                                        10   18   2   
61   5    )                                        10   19   5   
62   6    ;                                        10   20   5   
63   2    int                                      11   1    7   
64   1    gcd                                      11   5    1   
65   5    =                                        11   8    3   
66   1    gcd_cal                                  11   9    3   
67   5    (                                        11   16   6   
68   1    a                                        11   17   5   
69   6    ,                                        11   18   6   
70   1    b                                        11   19   3   
71   5    )                                        11   20   6   
72   6    ;                                        11   21   6   
73   1    printf                                   12   1    1   
74   5    (                                        12   7    7   
75   1    "gcd = %d; lcm = %d\n"                   12   8    1   
76   6    ,                                        12   30   7   
77   1    gcd                                      12   31   2   
78   6    ,                                        12   34   8   
79   1    a                                        12   35   6   
80   5    *                                        12   36   1   
81   1    b                                        12   37   4   
82   5    /                                        12   38   1   
83   1    gcd                                      12   39   3   
84   5    )                                        12   42   7   
85   6    ;                                        12   43   7   
86   2    return                                   13   1    2   
87   3    0                                        13   8    1   
88   6    ;                                        13   9    8   
89   6    }                                        14   1    3   
