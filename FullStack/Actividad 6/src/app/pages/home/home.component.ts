import { Component, inject } from '@angular/core';
import { IResponse, IUser } from '../../interfaces/iuser.interface';
import { UsersService } from '../../services/users.service';
import { UserCardComponent } from "../../components/user-card/user-card.component";
import Swal from 'sweetalert2';
@Component({
    selector: 'app-home',
    imports: [UserCardComponent],
    templateUrl: './home.component.html',
    styleUrl: './home.component.css',
})
export class HomeComponent {
    arrUsersPromises: IUser[] = [];
    userService = inject(UsersService);
    currentPage = 1
    totalPages = 1
    totalPagesArray: number[] = []

    ngOnInit() {
        this.loadUsers(this.currentPage)
    }

    async loadUsers(page: number) {
        try {
            const response: IResponse = await this.userService.getAllPromises(page)
            this.arrUsersPromises = response.results
            this.currentPage = response.page
            this.totalPages = response.total_pages
            this.totalPagesArray = []
            for(let i = 1; i <= this.totalPages; i++){
                this.totalPagesArray.push(i)
            }
        } catch (msg: any) {
          console.log(msg.error);
        }
      }

    changePage(page: number){
        if(page >= 1 && page <= this.totalPages){
            this.loadUsers(page)
        }
    }

    //"Load" Users again when "deleting" a new user
    onDeleteUser(msg: string){
        this.loadUsers(1)
        Swal.fire({
        position: "bottom-end",
        text: msg,
        showConfirmButton: false,
        timer: 1500,
        background: "#98FF98"
        });
    }
}
