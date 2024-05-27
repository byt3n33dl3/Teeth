using laget.HashId.Exceptions;
using laget.HashId.Tests.Abstractions;
using laget.HashId.Tests.Models;
using Newtonsoft.Json;
using Xunit;

namespace laget.HashId.Tests
{
    public class HashIdTest : TestBase
    {
        [Fact]
        public void ThrowsErrorOnUnknownHashVersion()
        {
            var hashId = HashId.FromString($"{HashVersion2X}bogusHash");
            Assert.Throws<HashIdInvalidVersionException>(() =>
            {
                var id = hashId.ToLong();
            });
        }

        [Fact]
        public void ThrowsErrorIfNotRegistered()
        {
            HashId.SetHashIdFactory(null);

            Assert.Throws<HashIdNotRegisteredException>(() => HashId.FromLong(1));

            HashId.SetHashIdFactory(HashIdFactory);
        }

        [Fact]
        public void IsProperlySerializedWithNewtonsoft()
        {
            const long id = 1234;
            var model = new Model { Id = HashId.FromLong(id) };

            var expectedJson = $"{{\"Id\":\"{model.Id.Hash}\"}}";
            var json = JsonConvert.SerializeObject(model);

            Assert.Equal(expectedJson, json);
        }

        [Fact]
        public void IsProperlyDeserializedWithNewtonsoft()
        {
            const long id = 1234;
            var model = new Model { Id = HashId.FromLong(id) };
            var json = JsonConvert.SerializeObject(model);

            var deserializedDto = JsonConvert.DeserializeObject<Model>(json);

            Assert.Equal(model.Id, deserializedDto.Id);
        }

        [Fact]
        public void NumericIdIsProperlyExtractedFromHashWithNewtonsoft()
        {
            const long id = 1234;
            var model = new Model { Id = HashId.FromLong(id) };
            var json = JsonConvert.SerializeObject(model);

            var deserializedDto = JsonConvert.DeserializeObject<Model>(json);
            var deserializedId = deserializedDto.Id.ToLong();

            Assert.Equal(id, deserializedId);
        }

        [Fact]
        public void NumericIdIntIsProperlyExtractedFromHashWithNewtonsoft()
        {
            const int id = 1234;
            var model = new Model { Id = HashId.FromInt(id) };
            var json = JsonConvert.SerializeObject(model);

            var deserializedDto = JsonConvert.DeserializeObject<Model>(json);
            var deserializedId = deserializedDto.Id.ToInt();

            Assert.Equal(id, deserializedId);
        }

        [Fact]
        public void ShouldHandleExplicitOperator()
        {
            const string expected = "0xR4reL0zL3Xgq8";
            var actual = (HashId)"0xR4reL0zL3Xgq8";

            Assert.Equal(expected, actual.Hash);
        }
    }
}