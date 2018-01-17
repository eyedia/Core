#region Copyright Notice
/* Copyright (c) 2017, Deb'jyoti Das - debjyoti@debjyoti.com
 All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are not permitted.Neither the name of the 
 'Deb'jyoti Das' nor the names of its contributors may be used 
 to endorse or promote products derived from this software without 
 specific prior written permission.
 THIS SOFTWARE IS PROVIDED BY Deb'jyoti Das 'AS IS' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL Debjyoti OR Deb'jyoti OR Debojyoti Das OR Eyedia BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#region Developer Information
/*
Author  - Deb'jyoti Das
Created - 3/19/2013 11:14:16 AM
Description  - 
Modified By - 
Description  - 
*/
#endregion Developer Information

#endregion Copyright Notice


using System.Runtime.InteropServices;
using System.Diagnostics;

namespace Eyedia.Security.Test
{
    class Program
    {
        [DllImport(@"Eyedia.Security.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Authenticate(string user, string password);

        [DllImport(@"Eyedia.Security.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        private static extern string Encrypt(string plaintext);

        [DllImport(@"Eyedia.Security.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int IsEqual(string plaintext, string enctext);        

        static void Main(string[] args)
        {
            //**********************positive cases********************************************/  
            //long password
            string password_to_encrypt = "ababababccccccccababababccccccccababababccccccccxxx12ababababccccccccababababccccccccababababccccccccxxx12debjyoti";
            string encrypted_password = Encrypt(password_to_encrypt);
            string correct_test_password = "ababababccccccccababababccccccccababababccccccccxxx12ababababccccccccababababccccccccababababccccccccxxx12debjyoti";
            int result = IsEqual(correct_test_password, encrypted_password);
            Debug.Assert(result == 1, "long password failed");

            //standard password
            password_to_encrypt = "password123";
            encrypted_password = Encrypt(password_to_encrypt);
            correct_test_password = "password123";
            result = IsEqual(correct_test_password, encrypted_password);
            Debug.Assert(result == 1, "standard password failed");

            //short password
            password_to_encrypt = "pass";
            encrypted_password = Encrypt(password_to_encrypt);
            correct_test_password = "pass";
            result = IsEqual(correct_test_password, encrypted_password);
            Debug.Assert(result == 1, "short password failed");

            //**********************negative cases********************************************/            
            password_to_encrypt = "password123";
            encrypted_password = Encrypt(password_to_encrypt);
            string incorrect_test_password = "somethingelse";
            result = IsEqual(incorrect_test_password, encrypted_password);
            Debug.Assert(result == 0, "negative test password failed");
        }
    }
}
