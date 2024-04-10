from typing import Annotated
from fastapi import FastAPI, Form

app = FastAPI()


@app.post("/")
def root(
    studentid: Annotated[str, Form()],
    name: Annotated[str, Form()],
    email: Annotated[str, Form()],
):
    print(studentid, name, email)
    return "OK"
