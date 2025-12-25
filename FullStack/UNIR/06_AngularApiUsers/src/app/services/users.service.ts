import { inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { lastValueFrom } from 'rxjs';
import { IError, IResponse, IUser } from '../interfaces/iuser.interface';
@Injectable({
    providedIn: 'root'
})
export class UsersService {
    private httpClient = inject(HttpClient)
    private baseUrl: string = "https://peticiones.online/api/users"

    //Gets the response of the api depending on the page we choose
    getAllPromises(page: number = 1): Promise<IResponse>{
        return lastValueFrom(this.httpClient.get<IResponse>(`${this.baseUrl}?page=${page}`))
    }

    //Gets the user based on the id
    getById(_id: string): Promise<any>{
        return lastValueFrom(this.httpClient.get<IUser>(`${this.baseUrl}/${_id}`))
    }

    //"Adds" a new user to the api
    insert(user: IUser): Promise<IUser> {
        return lastValueFrom(this.httpClient.post<IUser>(this.baseUrl, user))
    }

    //"Updates" the user on the api
    update(user: IUser): Promise<IUser> {
        let {_id, ...restUser} = user
        return lastValueFrom(this.httpClient.put<IUser>(`${this.baseUrl}/${_id}`, restUser))
    }

    //"Removes" the user from the api
    remove(_id: string): Promise<IUser|IError>{
        return lastValueFrom(this.httpClient.delete<IUser|any>(`${this.baseUrl}/${_id}`))
    }
}
