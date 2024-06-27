using laget.HashId.Tests.Abstractions;
using Xunit;

namespace laget.HashId.Tests
{
    public class EqualityTests : TestBase
    {
        [Fact]
        public void HashIdEqualHashId()
        {
            const int hashId1 = 1;
            const int hashId2 = 2;

            var hash1 = HashId.FromInt(hashId1);
            var hash2 = HashId.FromInt(hashId2);

            Assert.Equal(hash1, hash1);
            Assert.Equal(hash2, hash2);
            Assert.True(hash1 == hash1);
            Assert.True(hash2 == hash2);
        }

        [Fact]
        public void HashIdNotEqualHashId()
        {
            const int hashId1 = 3;
            const int hashId2 = 4;

            var hash1 = HashId.FromInt(hashId1);
            var hash2 = HashId.FromInt(hashId2);

            Assert.NotEqual(hash1, hash2);
            Assert.NotEqual(hash2, hash1);
            Assert.False(hash1 == hash2);
            Assert.False(hash2 == hash1);
            Assert.True(hash1 != hash2);
            Assert.True(hash2 != hash1);
        }

        [Fact]
        public void HashIdNotEqualNullableHash()
        {
            const int hashId2 = 4;

            HashId hash1 = null;
            var hash2 = HashId.FromInt(hashId2);

            Assert.False(hash1 == hash2);
            Assert.False(hash2 == hash1);
        }
    }
}
