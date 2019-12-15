curl -d '{"test":"testicles", "key2":"value2"}' \
      -H "Content-Type: application/json" \
      -X POST http://localhost:3000/create/test/testicles

curl -d '{"class_id": 39}' \
      -H "Content-Type: application/json" \
      -X POST http://localhost:3000/read/sample_training/grades

curl -d '{"key1":"value1", "key2":"value2"}' \
      -H "Content-Type: application/json" \
      -X POST http://localhost:3000/delete/corgis/charlie

