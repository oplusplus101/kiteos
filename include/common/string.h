
#include <common/types.h>

namespace kiteos
{
    namespace common
    {
        class string
        {
            char *value;
        public:
            string(char *str);
            ~string();

            void deleteLast();

        public:
            int32_t length();
            char *c_str();
            string operator =(char *str);
            bool operator ==(string x);
            string operator +=(char *str);
        };

    } // namespace common

} // namespace kiteos
