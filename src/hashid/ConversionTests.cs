using laget.HashId.Extensions;
using laget.HashId.Tests.Abstractions;
using Xunit;

namespace laget.HashId.Tests
{
    public class ConversionTests : TestBase
    {
        [Fact]
        public void ShouldBeCastToInt()
        {
            const int hashId = 1;
            var hash = HashId.FromInt(hashId);
            var model = new IntModel { Value = (int)hash };

            Assert.Equal(1, hash.ToInt());
            Assert.Equal(1, (int)hash);
            Assert.Equal(1, model.Value);
        }

        [Fact]
        public void ShouldBeCastNullableInt()
        {
            var model = new NullableIntModel { Value = null };
            var hash = model.Value.ToHashId();

            Assert.Null(hash);
        }

        [Fact]
        public void ShouldBeCastToLong()
        {
            const int hashId = 1;
            var hash = HashId.FromInt(hashId);
            var model = new LongModel { Value = (long)hash };

            Assert.Equal(1, hash.ToLong());
            Assert.Equal(1, (long)hash);
            Assert.Equal(1, model.Value);
        }

        [Fact]
        public void ShouldBeCastNullableLong()
        {
            var model = new NullableLongModel { Value = null };
            var hash = model.Value.ToHashId();

            Assert.Null(hash);
        }

        [Fact]
        public void ShouldBeCastToString()
        {
            const int hashId = 1;
            var hash = HashId.FromInt(hashId);
            var model = new StringModel { Value = (string)hash };

            Assert.Equal("0xR4reL0zL3Xgq8", hash.ToString());
            Assert.Equal("0xR4reL0zL3Xgq8", (string)hash);
            Assert.Equal("0xR4reL0zL3Xgq8", model.Value);
        }

        [Fact]
        public void ShouldBeCastNullableString()
        {
            var model = new StringModel { Value = null };
            var hash = model.Value.ToHashId();

            Assert.Null(hash);
        }

        internal class IntModel
        {
            public int Value { get; set; }
        }

        internal class NullableIntModel
        {
            public int? Value { get; set; }
        }

        internal class LongModel
        {
            public long Value { get; set; }
        }

        internal class NullableLongModel
        {
            public long? Value { get; set; }
        }

        internal class StringModel
        {
            public string Value { get; set; }
        }
    }
}
