using laget.HashId.Util;
using Microsoft.Extensions.Configuration;
using System.Collections.Generic;
using Xunit;

namespace laget.HashId.Tests.Util
{
    public class HashIdFactoryTest
    {
        [Fact]
        public void ProperlyParsesConfig()
        {
            const string defaultHashVersion = "0x";
            const string hashVersion2 = "1x";

            const string version0XSalt = "qwer";
            const string version1XSalt = "asdf";

            var config = new Dictionary<string, string>
            {
                { "DefaultHashVersion", defaultHashVersion },
                { $"SaltVersions:{defaultHashVersion}", version0XSalt },
                { $"SaltVersions:{hashVersion2}", version1XSalt }
            };

            var options = new ConfigurationBuilder()
                .AddInMemoryCollection(config)
                .Build()
                .Get<HashIdFactoryOptions>();

            Assert.Equal(defaultHashVersion, options.DefaultHashVersion);
            Assert.Equal(version0XSalt, options.SaltVersions[defaultHashVersion]);
            Assert.Equal(version1XSalt, options.SaltVersions[hashVersion2]);
        }
    }
}
