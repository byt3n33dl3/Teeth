using laget.HashId.Extensions;
using laget.HashId.Tests.Abstractions;
using Xunit;

namespace laget.HashId.Tests
{
    public class ExtensionTests : TestBase
    {
        [Fact]
        public void ShouldConvertIntToHashId()
        {
            var hashId = 1;
            var hash = hashId.ToHashId();

            var expected = "0xR4reL0zL3Xgq8";
            Assert.Equal(expected, hash.Hash);
        }

        [Fact]
        public void ShouldConvertLongToHashId()
        {
            var hashId = (long)1;
            var hash = hashId.ToHashId();

            var expected = "0xR4reL0zL3Xgq8";
            Assert.Equal(expected, hash.Hash);
        }
    }
}
