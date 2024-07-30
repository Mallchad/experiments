bool debug = true;

template<typename ...t_streamable>
constexpr void print(t_streamable... args)
{
    if (debug)
    {
        (std::cout << ... << args) << "\n";
    }
}

class Solution {
public:
    string longestPalindrome(string s) {
        int i = 0;
        int i_same;
        char x_char;
        char cmp1;
        char cmp2;
        char cmp3;
        int grow;
        // This should actually be "even" rather than "symmetric"
        bool offset = 0;
        string tmp;
        string largest;
        print( "Input Size: ", s.size() );
         for (; i<s.size(); ++i)
         {
             i_same = i;
            print(i);
            tmp.clear();
            x_char = s[i];
            grow = 0;
            cmp1 = s[i];
            for (; i_same<s.size(); ++i_same)
            {
                cmp2 = s[ i_same ];
                print("offset search: ", cmp1, cmp2);
                if (cmp1 != cmp2) { offset = (i_same - i); break; }
            }
            for (;; ++grow)
            {
                cmp1 = (i-grow >= 0) ? s[ i-grow ] : 0x0;
                cmp2 = (i+grow+offset <= s.size()) ? s[ i+grow+offset ] : 0x1;
                print("i grow offset :", i, grow, offset, s[2] );
                print(cmp1, cmp2);
                if ( cmp1 != cmp2 || cmp1 == 0x0 || cmp2 == 0x1) { --grow; break; }
            }
            if (grow == 0 && offset) { tmp = s.substr( i, 2 ); print("standalone:", tmp); }
            else if (grow == 0) { tmp = s[0]; }
            else
            {
                tmp = s.substr( i-grow, (grow*2)+offset );
            }
            print(tmp);
            largest = (tmp.size() > largest.size()) ? tmp : largest;
            print( largest );
         }
         return largest;
    }
};
